package com.example.socialnetworkgui.domain.validator;

public interface Validator<T> {
    /**
     * validates the entity
     * @param entity
     * @throws ValidationException
     */
    void validate(T entity) throws ValidationException;
}