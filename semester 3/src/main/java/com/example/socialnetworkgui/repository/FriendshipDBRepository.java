package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.Tuple;
import com.example.socialnetworkgui.domain.User;
import org.postgresql.util.PSQLState;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class FriendshipDBRepository extends DBRepository<Tuple<Long, Long>, Friendship> {
    private final Repository<Long, User> userRepo;
    public FriendshipDBRepository(String url, String username, String password, Repository<Long, User> userRepo) {
        super(url, username, password);
        this.userRepo = userRepo;
    }

    @Override
    public Optional<Friendship> add(Friendship entity) {
        String add_friendship = "INSERT INTO friendships (id1, id2, start_date, direction) VALUES (?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(add_friendship);
        ){
            statement.setLong(1, entity.getUser1().getId());
            statement.setLong(2, entity.getUser2().getId());
            statement.setLong(3, entity.getStartDate().toEpochSecond(ZoneOffset.ofHours(0)));
            statement.setBoolean(4, entity.getDirection());

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

    public Optional<Friendship> remove(Tuple<Long, Long> id) {
        String delete_friendship = "DELETE FROM friendships WHERE (id1=? AND id2=?) OR (id1=? AND id2=?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(delete_friendship);
        ) {
            Friendship friendship = getEntity(id);
            if (friendship == null)
                return Optional.empty();
            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            statement.setLong(3, id.getRight());
            statement.setLong(4, id.getLeft());
            statement.executeUpdate();
            return Optional.of(friendship);
        } catch (SQLException e){
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Friendship getEntity(Tuple<Long, Long> id) {
        String sql_string = "SELECT * FROM friendships WHERE (id1=? AND id2=?) OR (id1=? AND id2=?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql_string);
        ){
            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            statement.setLong(3, id.getRight());
            statement.setLong(4, id.getLeft());

            try(ResultSet resultSet = statement.executeQuery();) {
                if (resultSet.next()) {
                    return getFriendship(resultSet);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Friendship> getAll() {
        Set<Friendship> friendships = new HashSet<>();
        String get_all = "SELECT * FROM friendships";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(get_all);
             ResultSet resultSet = statement.executeQuery();
        ){
            while (resultSet.next()) {
                Friendship newFriendship = getFriendship(resultSet);
                friendships.add(newFriendship);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return friendships;
    }

    @Override
    public Optional<Friendship> update(Friendship entity, Friendship newEntity) {
        String add_friendship = "UPDATE friendships SET (id1, id2, accepted) = (?, ?, ?) WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(add_friendship);
        ){
            statement.setLong(1, newEntity.getUser1().getId());
            statement.setLong(2, newEntity.getUser2().getId());
            statement.setBoolean(3, newEntity.getStatus());

            statement.setLong(4, entity.getUser1().getId());
            statement.setLong(5, entity.getUser2().getId());

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

    private Friendship getFriendship(ResultSet resultSet) throws SQLException {
        Long id1 = resultSet.getLong("id1");
        Long id2 = resultSet.getLong("id2");
        LocalDateTime dateTime = LocalDateTime.ofEpochSecond(resultSet.getLong("start_date"), 0, ZoneOffset.ofHours(0));
        Boolean accepted = resultSet.getBoolean("accepted");
        Boolean fromUser1 = resultSet.getBoolean("direction");

        User user1 = userRepo.getEntity(id1);
        User user2 = userRepo.getEntity(id2);
        return new Friendship(user1, user2, dateTime, accepted, fromUser1);
    }
}
