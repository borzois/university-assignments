package com.example.socialnetworkgui.repository;

import com.example.socialnetworkgui.domain.Entity;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Optional;

public abstract class FileRepository<ID, E extends Entity<ID>> extends MemoryRepository<ID, E> {
    private String filename;

    public FileRepository(String filename) {
        this.filename = filename;
    }

    /**
     * loads the data from the file
     */
    protected void load() {
        Path path = Paths.get(filename);
        try {
            List<String> lines = Files.readAllLines(path);
            lines.forEach(line -> {
                E entity = entityFromString(line);
                super.add(entity);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * parses a line of the file
     * @param line the line
     * @return entity
     */
    public abstract E entityFromString(String line);

    /**
     * encodes the entity information
     * @param entity the entity
     * @return encoded as a string
     */
    protected abstract String stringFromEntity(E entity);

    @Override
    public Optional<E> add(E entity) {
        Optional<E> optional = super.add(entity);
        if (optional.isPresent()) {
            return optional;
        }
        writeToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<E> remove(ID id) {
        Optional<E> optional = super.remove(id);
        if (optional.isEmpty()) {
            return Optional.empty();
        }
        rewriteFile();
        return optional;
    }

    @Override
    public Optional<E> update(E entity, E newEntity) {
        return Optional.empty();
    }

//    @Override
//    public Optional<E> update(E entity) {
//        Optional<E> optional = super.update(entity);
//        if (optional.isPresent()) {
//            return optional;
//        }
//        rewriteFile();
//        return Optional.empty();
//    }

    /**
     * writes all the entities to the file, without appending
     */
    protected void rewriteFile() {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(filename,false))) {
            for (E entity : entities.values()) {
                bW.write(stringFromEntity(entity));
                bW.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * appends a single entity to the file
     * @param entity the new entity
     */
    protected void writeToFile(E entity) {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(filename,true))) {
            bW.write(stringFromEntity(entity));
            bW.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}