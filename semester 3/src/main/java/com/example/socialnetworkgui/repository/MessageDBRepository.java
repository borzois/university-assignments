package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.Message;
import com.example.socialnetworkgui.domain.User;
import org.postgresql.util.PSQLState;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.*;

// observatie:
// se poate adapta la interfata de repository doar daca fac filtrarea mesajelor in service
// in loc de sql
public class MessageDBRepository extends DBRepository<Long, Message> {
    public MessageDBRepository(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    public Iterable<Message> getAll() {
        Set<Message> messages = new HashSet<>();
        String get_all = "SELECT * FROM messages";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(get_all);
             ResultSet resultSet = statement.executeQuery();
        ){
            while (resultSet.next()) {
                Message newMessage = getMessage(resultSet);
                messages.add(newMessage);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return messages;
    }

    public Iterable<Message> getConversation(Long id1, Long id2) {
        Vector<Message> conversation = new Vector<Message>();
        String sql_string = "SELECT * FROM messages WHERE (id1=? AND id2=?) OR (id1=? AND id2=?) ORDER BY date";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql_string);
        ){
            statement.setLong(1, id1);
            statement.setLong(2, id2);
            statement.setLong(3, id2);
            statement.setLong(4, id1);

            try(ResultSet resultSet = statement.executeQuery();) {
                while (resultSet.next()) {
                    Message newMessage = getMessage(resultSet);
                    conversation.add(newMessage);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return conversation;
    }

    @Override
    public Optional<Message> add(Message entity) {
        String add_message = "INSERT INTO messages VALUES (?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(add_message);
        ){
            statement.setLong(1, entity.getId1());
            statement.setLong(2, entity.getId2());
            statement.setString(3, entity.getText());
            statement.setLong(4, entity.getDate().toEpochSecond(ZoneOffset.ofHours(0)));

            statement.executeUpdate();
        } catch (SQLException e){
            e.printStackTrace(); // change
        }
        return Optional.empty();
    }

    @Override
    public Optional<Message> remove(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Message> update(Message entity, Message newEntity) {
        return Optional.empty();
    }

    @Override
    public Message getEntity(Long aLong) {
        return null;
    }

    private Message getMessage(ResultSet resultSet) throws SQLException {
        Long id1 = resultSet.getLong("id1");
        Long id2 = resultSet.getLong("id2");
        String text = resultSet.getString("text");
        LocalDateTime date = LocalDateTime.ofEpochSecond(resultSet.getLong("date"), 0, ZoneOffset.ofHours(0));
        return new Message(id1, id2, text, date);
    }
}
