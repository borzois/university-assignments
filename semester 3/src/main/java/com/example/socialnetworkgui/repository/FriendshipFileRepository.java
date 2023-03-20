package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.Entity;
import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.Tuple;
import com.example.socialnetworkgui.domain.User;

import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.Arrays;
import java.util.List;

public class FriendshipFileRepository extends FileRepository<Tuple<Long, Long>, Friendship> {

    private Repository<Long, User> userRepo;
    public FriendshipFileRepository(String filename, Repository<Long, User> userRepository) {
        super(filename);
        this.userRepo = userRepository;
        load(); // load trebuie sa se execute dupa ce userRepo e definit
    }

    @Override
    public Friendship entityFromString(String line) {
        List<String> stringList = Arrays.asList(line.split(";"));
        Long id1 = Long.valueOf(stringList.get(0));
        Long id2 = Long.valueOf(stringList.get(1));
        long time = Long.parseLong(stringList.get(2));

        Tuple<Long, Long> id = new Tuple<>(id1, id2);

        User user1 = userRepo.getEntity(id1);
        User user2 = userRepo.getEntity(id2);

        Friendship f = new Friendship(user1, user2, LocalDateTime.ofEpochSecond(time, 0, ZoneOffset.ofHours(0)), false, false);
        f.setId(id);
        return f;
    }

    @Override
    protected String stringFromEntity(Friendship entity) {
        return entity.getId().getLeft() + ";" + entity.getId().getRight() +
                ";" + entity.getStartDate().toEpochSecond(ZoneOffset.ofHours(0));

    }
}
