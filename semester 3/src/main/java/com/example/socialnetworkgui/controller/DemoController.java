package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.domain.User;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import com.example.socialnetworkgui.utils.events.ChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observer;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class DemoController implements Observer<ChangeEvent> {
    UserService userService;
    ObservableList<User> model = FXCollections.observableArrayList();


    @FXML
    TableView<User> tableView;
    @FXML
    TableColumn<User, String> tableColumnName;


    public void setUserService(UserService userService) {
        this.userService = userService;
        userService.addObserver(this);
        initModel();
    }

    @FXML
    public void initialize() {
        tableColumnName.setCellValueFactory(new PropertyValueFactory<User, String>("name"));
        tableView.setItems(model);
    }

    private void initModel() {
        Iterable<User> messages = userService.getAllUsers();
        List<User> users = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
    }

    @Override
    public void update(ChangeEvent userChangeEvent) {
        initModel();
    }

    public void handleAddUser(ActionEvent actionEvent) {
        System.out.println("OKKK");
    }
    public void handleDeleteUser(ActionEvent actionEvent) {
        System.out.println("OKKK2");
    }

//    public void handleAddUser(ActionEvent actionEvent) {
//        User user = new User();
//        try{
//            User saved = userService.addUser(user);
//        } catch (ValidationException e){
//            MessageAlert.showErrorMessage(null, e.getMessage());
//            return;
//        }
//        MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Info", "User adaugat cu succes!");
////        if(service.addUtilizator(user) == null){
////            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Info", "User adaugat cu succes!");
////        } else{
////            MessageAlert.showErrorMessage(null, "Failed adding user");
////        }
//    }

//    public void handleDeleteUtilizator(ActionEvent actionEvent) {
//        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
//        if (user!=null) {
//            Utilizator deleted= userService.deleteUtilizator(user.getId());
//        }
//    }
//
//    public void handleUpdateUtilizator(ActionEvent actionEvent) {
//    }


//    public void handleDeleteMessage(ActionEvent actionEvent) {
//        MessageTask selected = (MessageTask) tableView.getSelectionModel().getSelectedItem();
//        if (selected != null) {
//            MessageTask deleted = service.deleteMessageTask(selected);
//            if (null != deleted)
//                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Delete", "Studentul a fost sters cu succes!");
//        } else MessageAlert.showErrorMessage(null, "Nu ati selectat nici un student!");
//    }
//

//
//    @FXML
//    public void handleUpdateMessage(ActionEvent ev) {
//        MessageTask selected = tableView.getSelectionModel().getSelectedItem();
//        if (selected != null) {
//            showMessageTaskEditDialog(selected);
//        } else
//            MessageAlert.showErrorMessage(null, "NU ati selectat nici un student");
//    }
//
//    @FXML
//    public void handleAddMessage(ActionEvent ev) {
//
//        showMessageTaskEditDialog(null);
//    }
//
//    public void showMessageTaskEditDialog(MessageTask messageTask) {
//        try {
//            // create a new stage for the popup dialog.
//            FXMLLoader loader = new FXMLLoader();
//            loader.setLocation(getClass().getResource("/views/editMessageTaskView.fxml"));
//
//            AnchorPane root = (AnchorPane) loader.load();
//
//            // Create the dialog Stage.
//            Stage dialogStage = new Stage();
//            dialogStage.setTitle("Edit Message");
//            dialogStage.initModality(Modality.WINDOW_MODAL);
//            //dialogStage.initOwner(primaryStage);
//            Scene scene = new Scene(root);
//            dialogStage.setScene(scene);
//
//            EditMessageTaskController editMessageViewController = loader.getController();
//            editMessageViewController.setService(service, dialogStage, messageTask);
//
//            dialogStage.show();
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//


}
