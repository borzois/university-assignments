package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.User;

import java.util.Arrays;
import java.util.List;

public class UserFileRepository extends FileRepository<Long, User> {

    public UserFileRepository(String filename) {
        super(filename);
        load();
    }

    @Override
    public User entityFromString(String line) {
        List<String> stringList = Arrays.asList(line.split(";"));
        Long id = Long.valueOf(stringList.get(0));
        String name = stringList.get(1);
        return new User(id, name);
    }

    @Override
    protected String stringFromEntity(User entity) {
        return String.valueOf(entity.getId()) + ';' + entity.getName();
    }
}
