package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.User;
import org.postgresql.util.PSQLState;

import java.sql.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class UserDBRepository extends DBRepository<Long, User> {
    public UserDBRepository(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    public Optional<User> add(User entity) {
        String add_user = "INSERT INTO users (name) VALUES (?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(add_user);
        ) {
             statement.setString(1,entity.getName());
             statement.executeUpdate();
        } catch (SQLException e){
            if (Objects.equals(e.getSQLState(), PSQLState.UNIQUE_VIOLATION.getState())) {
                return Optional.ofNullable(getEntity(entity.getId()));
            }
            else {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<User> remove(Long aLong) {
        String delete_user = "DELETE FROM users WHERE id=" + aLong.toString();
        String get_user = "SELECT * FROM users WHERE id=" + aLong.toString();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement getUserStatement = connection.prepareStatement(get_user);
             ResultSet resultSet = getUserStatement.executeQuery();
        ) {
            if (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                User user = new User(id, name);

                PreparedStatement statement = connection.prepareStatement(delete_user);
                statement.executeUpdate();
                return Optional.of(user);
            }
        } catch (SQLException e){
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public User getEntity(Long aLong) {
        String get_user = "SELECT * FROM users WHERE id=" + aLong.toString();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(get_user);
             ResultSet resultSet = statement.executeQuery();
        ) {
            if (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                return new User(id, name);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<User> getAll() {
        String get_all = "SELECT * FROM users";
        Set<User> users = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(get_all);
             ResultSet resultSet = statement.executeQuery();
        ) {
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                User new_user = new User(id, name);
                users.add(new_user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }

    @Override
    public Optional<User> update(User entity, User newEntity) {
        return Optional.empty();
    }
}
