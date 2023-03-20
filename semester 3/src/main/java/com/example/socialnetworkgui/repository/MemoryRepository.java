package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.Entity;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class MemoryRepository<ID, E extends Entity<ID>>  implements Repository<ID, E> {
    Map<ID, E> entities;

    public MemoryRepository() {
        entities = new HashMap<>();
    }

    @Override
    public Iterable<E> getAll() {
        return entities.values();
    }

    @Override
    public Optional<E> add(E entity) {
        if (entity==null)
            throw new IllegalArgumentException("ID cannot be null");

        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));
    }

    @Override
    public Optional<E> remove(ID id) {
        if (id == null)
            throw new IllegalArgumentException("ID cannot be null");
        return Optional.ofNullable(entities.remove(id));
    }

    @Override
    public Optional<E> update(E entity, E newEntity) {
        return Optional.empty();
    }

//    @Override
//    public Optional<E> update(E entity) {
//        if (entity == null) {
//            throw new IllegalArgumentException("Entity cannot be null");
//        }
//        return Optional.ofNullable(entities.computeIfPresent(entity.getId(), (k, v) -> entity));
//    }

    @Override
    public E getEntity(ID id) {
        if (id == null) throw new IllegalArgumentException("ID cannot be null");
        return entities.get(id);
    }
}
