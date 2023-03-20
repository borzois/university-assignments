package com.example.socialnetworkgui.domain.validator;

import com.example.socialnetworkgui.domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {
    @Override
    public void validate(Friendship entity) throws ValidationException {
        if (entity.getUser1() == null || entity.getUser2() == null) throw new ValidationException("Can not find users");
        if (entity.getUser1().equals(entity.getUser2())) throw new ValidationException("Users must be different");
    }
}
