package com.example.socialnetworkgui.repository;


import com.example.socialnetworkgui.domain.Entity;

public abstract class DBRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected String url;
    protected String username;
    protected String password;

    public DBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }
}
