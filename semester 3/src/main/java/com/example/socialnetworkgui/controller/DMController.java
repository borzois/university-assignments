package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.domain.Message;
import com.example.socialnetworkgui.service.UserService;
import com.example.socialnetworkgui.utils.events.ChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TableCell;
import javafx.scene.control.TextField;

import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;

public class DMController implements Observer<ChangeEvent> {
    ObservableList<Message> messages = FXCollections.observableArrayList();
    @FXML
    ListView<Message> messageListView = new ListView<>(messages);

    @FXML
    TextField fieldMessage;

    private UserService userService;
    private Long id1;
    private Long id2;

    @FXML
    public void initialize() {
        messageListView.setCellFactory(cell -> new ListCell<>() {
            @Override
            protected void updateItem(Message item, boolean empty) {
                super.updateItem(item, empty);
                if (!empty) {
                    setText("[" + item.getDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")) + "] " +
                            userService.getUser(item.getId1()).getName() + ": " + item.getText());
                }
            }
        });
        messageListView.setItems(messages);
    }

    public void initData(UserService userService, Long id1, Long id2) {
        this.userService = userService;
        this.id1 = id1;
        this.id2 = id2;

        messages.setAll(userService.getConversation(id1, id2));
        userService.addObserver(this);
    }

    public void handleSendMessage() {
        System.out.println("Sending " + fieldMessage.getText());
        userService.sendMessage(id1, id2, fieldMessage.getText());
        fieldMessage.clear();
    }

    @Override
    public void update(ChangeEvent changeEvent) {
        messages.setAll(userService.getConversation(id1, id2));
    }
}
