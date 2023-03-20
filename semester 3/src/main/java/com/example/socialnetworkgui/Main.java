package com.example.socialnetworkgui;

import com.example.socialnetworkgui.repository.FriendshipDBRepository;
import com.example.socialnetworkgui.repository.Repository;
import com.example.socialnetworkgui.repository.UserDBRepository;
import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.ui.UserInterface;
import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.Tuple;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.domain.validator.FriendshipValidator;
import com.example.socialnetworkgui.domain.validator.UserValidator;
import com.example.socialnetworkgui.domain.validator.Validator;

public class Main {
    public static void main(String[] args) {
        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();
        // Repository<Long, User> userRepo = new UserFileRepository("./database/users");
        // Repository<Tuple<Long, Long>, Friendship> friendshipRepo
        //                = new FriendshipFileRepository("./database/friends", userRepo);
        Repository<Long, User> userRepo = new UserDBRepository("jdbc:postgresql://localhost:5431/socialNetworkDB",
                "postgres", "postgres");
        Repository<Tuple<Long, Long>, Friendship> friendshipRepo = new FriendshipDBRepository("jdbc:postgresql://localhost:5431/socialNetworkDB",
                "postgres", "postgres", userRepo);
//        UserService service = new UserService(userRepo, friendshipRepo, messageRepo, userValidator, friendshipValidator);
//        UserInterface UI = new UserInterface(service);

//        UI.run();
    }
}