package com.example.socialnetworkgui;

import com.example.socialnetworkgui.controller.UserController;
import com.example.socialnetworkgui.repository.FriendshipDBRepository;
import com.example.socialnetworkgui.repository.MessageDBRepository;
import com.example.socialnetworkgui.repository.Repository;
import com.example.socialnetworkgui.repository.UserDBRepository;
import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.Tuple;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.domain.Message;
import com.example.socialnetworkgui.domain.validator.FriendshipValidator;
import com.example.socialnetworkgui.domain.validator.UserValidator;
import com.example.socialnetworkgui.domain.validator.Validator;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {

    Repository<Long, User> userRepo;
    UserService service;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        String username="postgres";
        String password="postgres";
        String url="jdbc:postgresql://localhost:5431/socialNetworkDB";

        Repository<Long, User> userRepo =
                new UserDBRepository(url,username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepo = new FriendshipDBRepository(url, username, password, userRepo);
        Repository<Long, Message> messageRepo = new MessageDBRepository(url, username, password);

        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();

        userRepo.getAll().forEach(System.out::println);

        service = new UserService(userRepo, friendshipRepo, messageRepo, userValidator, friendshipValidator);
        initView(primaryStage);
        primaryStage.setWidth(825);
        primaryStage.setResizable(false);
        primaryStage.setTitle("Social Network");
        primaryStage.show();
    }

    private void initView(Stage primaryStage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/UserView.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        UserController userController = fxmlLoader.getController();
        userController.setUserService(service);
    }
}

// Repo interface?
// State variables?