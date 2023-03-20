package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.HelloApplication;
import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.domain.validator.ValidationException;
import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.utils.events.ChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UserController implements Observer<ChangeEvent> {
    private UserService userService;
    private User selectedUser;
    private boolean isFilteringFriends;
    private boolean isShowingRequests;

    /*-------------------------*/
    ObservableList<User> userModel = FXCollections.observableArrayList();
    @FXML
    TableView<User> userTableView;
    @FXML
    TableColumn<User, String> colName;
    @FXML
    TableColumn<User, Long> colID;

    /*-------------------------*/
    ObservableList<Friendship> sentRequestModel = FXCollections.observableArrayList();
    @FXML
    TableView<Friendship> sentRequestTableView;
    @FXML
    TableColumn<Friendship, LocalDateTime> colSentRequestDate;
    @FXML
    TableColumn<Friendship, Long> colSentRequestUser;
    @FXML
    TableColumn<Friendship, Boolean> colSentRequestStatus;

    /*-------------------------*/

    ObservableList<Friendship> receivedRequestModel = FXCollections.observableArrayList();
    @FXML
    TableView<Friendship> receivedRequestTableView;
    @FXML
    TableColumn<Friendship, LocalDateTime> colReceivedRequestDate;
    @FXML
    TableColumn<Friendship, Long> colReceivedRequestUser;
    @FXML
    TableColumn<Friendship, Boolean> colReceivedRequestStatus;

    /*-------------------------*/

    @FXML
    TextField fieldSearchUser;

    @FXML
    Label labelCurrentUser;

    @FXML
    public void initialize() {
        colID.setCellValueFactory(new PropertyValueFactory<>("id"));
        colName.setCellValueFactory(new PropertyValueFactory<>("name"));
        userTableView.setItems(userModel);

        colSentRequestUser.setCellValueFactory(new PropertyValueFactory<>("requesteeName"));
        colSentRequestDate.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        colSentRequestStatus.setCellValueFactory(new PropertyValueFactory<>("status"));
        colSentRequestStatus.setCellFactory(col -> new TableCell<>() {
            @Override
            protected void updateItem(Boolean item, boolean empty) {
                super.updateItem(item, empty) ;
                setText(empty ? null : item ? "accepted" : "pending" );
                setTextFill(Color.WHITE);
            }
        });
        sentRequestTableView.setItems(sentRequestModel);

        colReceivedRequestUser.setCellValueFactory(new PropertyValueFactory<>("requesterName"));
        colReceivedRequestDate.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        colReceivedRequestStatus.setCellValueFactory(new PropertyValueFactory<>("status"));
        colReceivedRequestStatus.setCellFactory(col -> new TableCell<>() {
            @Override
            protected void updateItem(Boolean item, boolean empty) {
                super.updateItem(item, empty) ;
                setText(empty ? null : item ? "accepted" : "pending" );
                setTextFill(Color.WHITE);
            }
        });
        receivedRequestTableView.setItems(receivedRequestModel);

        labelCurrentUser.setText("No user selected");
    }

    public void setUserService(UserService userService) {
        this.userService = userService;
        userService.addObserver(this);
        initUserModel();
    }

    private void initUserModel() {
        if (selectedUser != null && isFilteringFriends) {
            userModel.setAll(userService.getFriends(selectedUser));
        }
        else {
            Iterable<User> userIterable = userService.getAllUsers();
            List<User> users = StreamSupport.stream(userIterable.spliterator(), false)
                    .collect(Collectors.toList());
            userModel.setAll(users);
        }
    }

    private void initFriendRequestModel() {
        if (selectedUser != null && isShowingRequests) {
            Iterable<Friendship> friendshipIterable = userService.getAllFriendships();
            List<Friendship> sentRequests = StreamSupport.stream(friendshipIterable.spliterator(), false)
                    .filter(f -> (f.getUser1().equals(selectedUser) && f.getDirection())
                            || (f.getUser2().equals(selectedUser) && !f.getDirection()))
                    .toList();
            List<Friendship> receivedRequests = StreamSupport.stream(friendshipIterable.spliterator(), false)
                    .filter(f -> (f.getUser1().equals(selectedUser) && !f.getDirection())
                            || (f.getUser2().equals(selectedUser) && f.getDirection()))
                    .toList();
            sentRequestModel.setAll(sentRequests);
            receivedRequestModel.setAll(receivedRequests);
        }
        else {
            sentRequestModel.clear();
            receivedRequestModel.clear();
        }
    }

    @Override
    public void update(ChangeEvent userChangeEvent) {
        initUserModel();
        initFriendRequestModel();
    }

    public void handleAddUser() {
        TextInputDialog dialog = new TextInputDialog();

        dialog.setTitle("Add User");
        dialog.setHeaderText("Add a new user");
        dialog.setContentText("Name:");

        Optional<String> result = dialog.showAndWait();
        String name = result.orElse(null);

        try {
            userService.addUser(1L, name);
            showAlert("User added", Alert.AlertType.INFORMATION);
        } catch (ValidationException e) {
            showAlert(e.getMessage(), Alert.AlertType.ERROR);
        }
    }

    public void handleRemoveUser() {
        TextInputDialog dialog = new TextInputDialog();

        dialog.setTitle("Remove User");
        dialog.setHeaderText("Remove a user");
        dialog.setContentText("ID:");

        Optional<String> result = dialog.showAndWait();
        if (result.isPresent()) {
            Long id = Long.parseLong(result.get());

            if (userService.removeUser(id).isPresent()) {
                showAlert("User removed", Alert.AlertType.INFORMATION);
            }
            else {
                showAlert("Could not find user", Alert.AlertType.ERROR);
            }
        }
    }

    public void handleSelectUser() {
//        User user = StreamSupport
//                .stream(userService.getAllUsers().spliterator(), false)
//                .filter(x -> Objects.equals(x.getId(), Long.parseLong(fieldSearchUser.getText())))
//                .findFirst()
//                .orElse(null);
//        System.out.println(user);
//        selectedUser = user;
//        fieldSearchUser.clear();
//        labelCurrentUser.setText("Current user: " + selectedUser.getName());

        TextInputDialog dialog = new TextInputDialog();

        dialog.setTitle("Log in");
        dialog.setHeaderText("Log in");
        dialog.setContentText("Username or id: ");

        Optional<String> result = dialog.showAndWait();
        String input = result.orElse(null);
        if (input == null)
            return;
        System.out.println(input);

        try {
            Long id = Long.parseLong(input);
            selectedUser = StreamSupport
                .stream(userService.getAllUsers().spliterator(), false)
                .filter(x -> Objects.equals(x.getId(), id))
                .findFirst()
                .orElse(null);
        } catch (NumberFormatException nfe) {
            selectedUser = StreamSupport
                    .stream(userService.getAllUsers().spliterator(), false)
                    .filter(x -> Objects.equals(x.getName(), input))
                    .findFirst()
                    .orElse(null);

        }
        if (selectedUser == null) return;

        isShowingRequests = false;
        isFilteringFriends = false;

        labelCurrentUser.setText("Current user: " + selectedUser.getName());
        initUserModel();
        initFriendRequestModel();
    }

    public void handleShowFriendRequests() {
        if (selectedUser != null) {
            isShowingRequests = !isShowingRequests;
            initFriendRequestModel();
        }
        else {
            showAlert("No user selected", Alert.AlertType.ERROR);
        }
    }

    public void handleAddFriend() {
        if (selectedUser == null) {
            showAlert("No user selected", Alert.AlertType.ERROR);
            return;
        }
        Long id1 = selectedUser.getId();

        TextInputDialog dialog = new TextInputDialog();

        dialog.setTitle("Add Friend");
        dialog.setHeaderText("Add a new friend");
        dialog.setContentText("Name:");

        Optional<String> result = dialog.showAndWait();
        if (result.isPresent()) {
            String userName2 = result.get();

            User user2 = StreamSupport
                    .stream(userService.getAllUsers().spliterator(), false)
                    .filter(x -> Objects.equals(x.getName(), userName2))
                    .findFirst()
                    .orElse(null);
            if (user2 == null) {
                showAlert("Could not find user", Alert.AlertType.ERROR);

            } else {
                try {
                    userService.addFriend(id1, user2.getId());
                    showAlert("Friend request sent", Alert.AlertType.INFORMATION);

                } catch (ValidationException e) {
                    showAlert(e.getMessage(), Alert.AlertType.ERROR);
                }
            }
        }
    }
    public void handleAcceptFriendRequest() {
        Friendship f = receivedRequestTableView.getSelectionModel().getSelectedItem();
        userService.acceptFriendRequest(f);
    }

    public void handleCancelFriendRequest() {
        Friendship f = sentRequestTableView.getSelectionModel().getSelectedItem();
        userService.removeFriend(f.getUser1().getId(), f.getUser2().getId());
    }

    public void handleRemoveFriend() {
        Long id1 = userTableView.getSelectionModel().getSelectedItem().getId();
        Long id2 = selectedUser.getId();
        System.out.println("removing friendship between" + id1 + id2);
        userService.removeFriend(id1, id2);
    }
    public void handleShowFriends() {
        if (selectedUser != null) {
            isFilteringFriends = !isFilteringFriends;
            initUserModel();
        }
        else {
            showAlert("No user selected", Alert.AlertType.ERROR);
        }
    }

    public void handleClearSearch() {
        selectedUser = null;
        initUserModel();
        initFriendRequestModel();
        labelCurrentUser.setText("No user selected");
    }

    public void handleOpenChat() {
        // popup window
        // chats are stored in the database
        // message: id1 id2 text date
        // SELECT * FROM MESSAGES WHERE id1 = user1.id AND id2 = user2.id ...

        if (selectedUser == null || userTableView.getSelectionModel().getSelectedItem() == null) {
            showAlert("No user selected", Alert.AlertType.ERROR);
            return;
        }
        Long id1 = selectedUser.getId();
        Long id2 = userTableView.getSelectionModel().getSelectedItem().getId();

        userService.getConversation(id1, id2).forEach(System.out::println);

        Parent root;
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/DMView.fxml"));
            root = fxmlLoader.load();

            Stage stage = new Stage();
            stage.setTitle("Direct Message with " + userService.getUser(id2).getName());
            stage.setScene(new Scene(root, 450, 450));
            stage.show();

            DMController dmController = fxmlLoader.getController();
            dmController.initData(userService, id1, id2);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showAlert(String message, Alert.AlertType alertType) {
        Alert alert = new Alert(alertType, message, ButtonType.OK);
        alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
        alert.getDialogPane().setStyle("-fx-background-color: #1A1A1A; -fx-text-fill: white;");

        GridPane grid = (GridPane)alert.getDialogPane().lookup(".header-panel");
        grid.setStyle("-fx-background-color: #1A1A1A; -fx-text-fill: white;");

        ButtonBar buttonBar = (ButtonBar)alert.getDialogPane().lookup(".button-bar");
        buttonBar.setStyle("-fx-background-color: #1A1A1A; -fx-text-fill: white;");

        alert.show();
    }
}
