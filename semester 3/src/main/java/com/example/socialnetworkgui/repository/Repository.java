package com.example.socialnetworkgui.repository;


import com.example.socialnetworkgui.domain.Entity;
import com.example.socialnetworkgui.domain.validator.ValidationException;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {
    /**
     * gets all the values from the repo
     * @return all entities
     */
    Iterable<E> getAll();

    /**
     * adds the entity to the repository
     * @param entity
     *         entity must be not null
     * @return null - if the given entity is saved
     *         otherwise returns the entity (id already exists)
     * @throws ValidationException
     *            if the entity is not valid
     * @throws IllegalArgumentException
     *             if the given entity is null.     *
     */
    Optional<E> add(E entity);

    /**
     * removes the entity with the specified id
     * @param id
     *      id must be not null
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException
     *                   if the given id is null.
     */
    Optional<E> remove(ID id);

    /**
     * updates the entity
     * @param entity the entity to update
     * @return null if the entity was updated
     */
    Optional<E> update(E entity, E newEntity);

    /**
     * gets the entity with a given id
     * @param id the id of the entity to be returned
     *           must not be null
     * @return the entity with the specified id
     * or null - if there is no entity with the given id
     * @throws IllegalArgumentException
     *                  if id is null.
     */
    E getEntity(ID id);
}
