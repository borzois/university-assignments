package com.example.socialnetworkgui.service;

import com.example.socialnetworkgui.repository.Repository;
import com.example.socialnetworkgui.domain.*;
import com.example.socialnetworkgui.utils.events.ChangeEventType;
import com.example.socialnetworkgui.utils.events.ChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observable;
import com.example.socialnetworkgui.utils.observer.Observer;

import com.example.socialnetworkgui.domain.validator.Validator;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.StreamSupport;

public class UserService implements Observable<ChangeEvent> {
    private List<Observer<ChangeEvent>> observers = new ArrayList<>();
    private final Repository<Long, User> userRepo;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepo;
    private final Repository<Long, Message> messageRepo;
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    public UserService(Repository<Long, User> userRepo,
                       Repository<Tuple<Long, Long>, Friendship> friendshipRepo,
                       Repository<Long, Message> messageRepo,
                       Validator<User> userValidator,
                       Validator<Friendship> friendshipValidator)
    {
        this.userRepo = userRepo;
        this.friendshipRepo = friendshipRepo;
        this.messageRepo = messageRepo;
        this.userValidator = userValidator;
        this.friendshipValidator = friendshipValidator;
    }

    public Vector<User> getFriends(User user) {
        Vector<User> friends = new Vector<>();
        for (Friendship f : friendshipRepo.getAll()) {
            if (f.getStatus()) {
                if (f.getUser1().equals(user)) {
                    friends.add(f.getUser2());
                } else if (f.getUser2().equals(user)) {
                    friends.add(f.getUser1());
                }
            }
        }
        return friends;
    }

    /**
     * @return all users in the repository
     */
    public Iterable<User> getAllUsers() {
        return userRepo.getAll();
    }

    /**
     * @return all users in the repository
     */
    public Iterable<Friendship> getAllFriendships() {
        return friendshipRepo.getAll();
    }

    /**
     * makes a new user and adds it to the repository
     * @param id id of the new user
     * @param name name of the new user
     */
    public Optional<User> addUser(Long id, String name) {
        User user = new User(id, name);
        userValidator.validate(user);
        Optional<User> result = userRepo.add(user);
        if (result.isEmpty()) {
            ChangeEvent event = new ChangeEvent(ChangeEventType.ADD);
            notifyObservers(event);
        }
        return result;
    }

    /**
     * removes a user from the repository
     * @param id id of the removed user
     */
    public Optional<User> removeUser(Long id) {
        User user = userRepo.getEntity(id);
        if (user != null) {
            for (User friend : getFriends(user)) {
                System.out.println("FRIEND " + friend);
                Tuple<Long, Long> f_id = new Tuple<Long, Long>(user.getId(), friend.getId());
                friendshipRepo.remove(f_id);
            }
        }
        Optional<User> result = userRepo.remove(id);
        if (result.isPresent()) {
            ChangeEvent event = new ChangeEvent(ChangeEventType.DELETE);
            notifyObservers(event);
        }
        return result;
    }

    public User getUser(Long id) {
        return userRepo.getEntity(id);
    }

    /**
     * creates a friendship between two users
     * @param id1 id of the first user
     * @param id2 id of the second user
     */
    public Optional<Friendship> addFriend(Long id1, Long id2) {
        User user1 = userRepo.getEntity(id1); // requester
        User user2 = userRepo.getEntity(id2);
        Boolean fromUser1 = true;
        if (user1 != null && user2 != null && user1.getId() > user2.getId()) {
            User user_swap = user1;
            user1 = user2;
            user2 = user_swap;
            fromUser1 = false;
        }

        Friendship f = new Friendship(user1, user2, fromUser1);
        friendshipValidator.validate(f);
        Tuple<Long, Long> id = new Tuple<Long, Long>(user1.getId(), user2.getId());
        f.setId(id);
        Optional<Friendship> result = friendshipRepo.add(f);
        if (result.isEmpty()) {
            ChangeEvent event = new ChangeEvent(ChangeEventType.ADD);
            notifyObservers(event);
        }
        return result;
    }

    /**
     * removes a friendship between two users
     * @param id1 id of the first user
     * @param id2 id of the second user
     */
    public Optional<Friendship> removeFriend(Long id1, Long id2) {
        Tuple<Long, Long> id = new Tuple<Long, Long>(id1, id2);
        Optional<Friendship> result = friendshipRepo.remove(id);
        if (result.isPresent()) {
            ChangeEvent event = new ChangeEvent(ChangeEventType.DELETE);
            notifyObservers(event);
        }
        return result;
    }

    public void acceptFriendRequest(Friendship friendship) {
        Friendship accepted = new Friendship(friendship.getUser1(),
                friendship.getUser2(), friendship.getStartDate(), true, friendship.getDirection());
        Optional<Friendship> result = friendshipRepo.update(friendship, accepted);
        if (result.isEmpty()) {
            ChangeEvent event = new ChangeEvent(ChangeEventType.UPDATE);
            notifyObservers(event);
        }
    }

    public List<Message> getConversation(Long id1, Long id2) {
        return StreamSupport
                .stream(messageRepo.getAll().spliterator(), false)
                .filter(x -> Objects.equals(x.getId1(), id1) && Objects.equals(x.getId2(), id2) ||
                        Objects.equals(x.getId1(), id2) && Objects.equals(x.getId2(), id1))
                .sorted(Comparator.comparing(Message::getDate))
                .toList();
    }

    public void sendMessage(Long id1, Long id2, String text) {
        Message message = new Message(id1, id2, text, LocalDateTime.now());
        System.out.println(message);

        messageRepo.add(message);
        ChangeEvent event = new ChangeEvent(ChangeEventType.ADD);
        notifyObservers(event);
    }

    /**
     * basic dfs
     * @param user current user
     * @param visited visited users
     */
    private void DFSUtil(User user, Set<User> visited)
    {
        visited.add(user);
        for (User n : getFriends(user))
        {
            if (!visited.contains(n))
                DFSUtil(n, visited);
        }
    }

    /**
     * @return number of communities (connected components)
     */
    public int getCommunities() {
        Iterable<User> users = userRepo.getAll();
        Set<User> visited = new HashSet<User>();
        int communities = 0;

        for (User u : users) {
            if (!visited.contains(u)) {
                DFSUtil(u, visited);
                communities++;
            }
        }
        return communities;
    }

    /**
     * dfs that keeps track of its path
     * @param user current user
     * @param visited visited users
     * @param currentPath the path taken by the current execution
     */
    private void DFSUtil2(User user, Set<User> visited, Vector<User> currentPath, Vector<User> longestPath)
    {
        visited.add(user);
        currentPath.add(user);
        if (currentPath.size() > longestPath.size()) {
            longestPath.clear();
            longestPath.addAll(currentPath);
        }
        for (User n : getFriends(user))
        {
            if (!visited.contains(n)) {
                DFSUtil2(n, visited, currentPath, longestPath);
            }
        }
        currentPath.remove(user);
    }

    /**
     * @return the community that contains the longest path
     */
    public Vector<User> getLargestCommunity() {
        Iterable<User> users = userRepo.getAll();
        Set<User> visited = new HashSet<User>();
        Vector<User> currentPath, longestPath;
        longestPath = new Vector<>();

        for (User u : users) {
            if (!visited.contains(u)) {
                currentPath = new Vector<>();
                DFSUtil2(u, visited, currentPath, longestPath);
            }
        }

        return longestPath;
    }

    @Override
    public void addObserver(Observer<ChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<ChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(ChangeEvent t) {
        observers.forEach(x -> x.update(t));
    }
}
