package com.example.socialnetworkgui.ui;

import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.domain.validator.ValidationException;
import com.example.socialnetworkgui.service.UserService;

import java.util.InputMismatchException;
import java.util.Optional;
import java.util.Scanner;
import java.util.Vector;

public class UserInterface {
    UserService userService;
    static Scanner scanner = new Scanner(System.in);

    public UserInterface(UserService userService) {
        this.userService = userService;
    }

    private static void printMenu() {
        System.out.print(
            """
            []-----[SOCIALNETWORK]-----[]
            |1. Add user                |
            |2. Remove user             |
            |                           |
            |3. Add friend              |
            |4. Remove friend           |
            |                           |
            |5. Show communities        |
            |6. Show largest community  |
            |                           |
            |9. Show users              |
            |0. Exit                    |
            []-------------------------[]
            """
        );
    }

    private void printUsers() {
        Iterable<User> users = userService.getAllUsers();
        Iterable<Friendship> friendships = userService.getAllFriendships();

        System.out.println("[]---------[USERS]---------[]");
        for (User user : users) {
            System.out.println(" " + user);
        }
        for (Friendship f : friendships) {
            System.out.println(" " + f);
        }
    }

    private void addUserUI() {
        long id;
        String name;
        try{
            System.out.print("ID: ");
            id = scanner.nextLong();
            System.out.print("Name: ");
            scanner.nextLine();
            name = scanner.nextLine();
            if (userService.addUser(id, name).isPresent())
                System.out.println("A user with that ID already exists");
            else
                System.out.println("User added successfully");
        } catch (InputMismatchException e) {
            System.out.println("ID must be a number");
            scanner.nextLine();
        } catch (ValidationException v) {
            System.out.println(v.getMessage());
        }
    }

    private void removeUserUI() {
        long id;

        try {
            System.out.print("ID: ");
            id = scanner.nextInt();

            Optional<User> result = userService.removeUser(id);
            if (result.isPresent())
                System.out.println("Removed user " + result.get());
            else
                System.out.println("Could not find user");
        } catch (InputMismatchException e) {
            System.out.println("ID must be a number");
            scanner.nextLine();
        }
    }

    private void addFriendUI() {
        long id1, id2;
        try {
            System.out.print("ID 1: ");
            id1 = scanner.nextInt();
            System.out.print("ID 2: ");
            id2 = scanner.nextInt();

            Optional<Friendship> result = userService.addFriend(id1, id2);
            if (result.isPresent())
                System.out.println("Friendship already exists: " + result.get());
            else
                System.out.println("Friendship added");
        } catch (InputMismatchException e) {
            System.out.println("ID must be a number");
            scanner.nextLine();
        } catch (ValidationException v) {
            System.out.println(v.getMessage());
            scanner.nextLine();
        }
    }

    private void removeFriendUI() {
        long id1, id2;
        try {
            System.out.print("ID 1: ");
            id1 = scanner.nextInt();
            System.out.print("ID 2: ");
            id2 = scanner.nextInt();
            Optional<Friendship> result = userService.removeFriend(id1, id2);
            if (result.isPresent())
                System.out.println("Removed friendship " + result.get());
            else
                System.out.println("Could not find friendship");
        } catch (InputMismatchException e) {
            System.out.println("ID must be a number");
            scanner.nextLine();
        }
    }

    private void showCommunitiesUI() {
        int communities = userService.getCommunities();
        if (communities == 1) System.out.println("1 community");
        else System.out.println(communities + " communities");
    }

    private void showLargestCommunityUI() {
        System.out.println("Largest community:");
        Vector<User> community = userService.getLargestCommunity();
        for (User u : community) {
            System.out.print(u + " ");
        }
        System.out.println("\nsize: " + (community.size()-1));
    }

    public void run() {
        while (true) {
            printMenu();

            int option;
            try {
                option = scanner.nextInt();
                System.out.println("Option " + option);
            } catch (InputMismatchException e) {
                System.out.println("Option must be a number");
                scanner.nextLine();
                continue;
            }

            switch (option) {
                case 1 -> addUserUI();
                case 2 -> removeUserUI();

                case 3 -> addFriendUI();
                case 4 -> removeFriendUI();

                case 5 -> showCommunitiesUI();
                case 6 -> showLargestCommunityUI();

                case 9 -> printUsers();
                case 0 -> System.exit(0);
                default -> System.out.println("Invalid option");
            }
        }
    }
}
