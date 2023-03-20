package com.example.socialnetworkgui.domain.validator;

import com.example.socialnetworkgui.domain.User;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        if (entity.getName().equals("")) throw new ValidationException("Name cannot be empty");
        if (entity.getId() <= 0) throw new ValidationException("ID must be larger than 0");
    }
}
