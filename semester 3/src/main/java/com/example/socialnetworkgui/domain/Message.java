package com.example.socialnetworkgui.domain;

import java.time.LocalDateTime;

public class Message extends Entity<Long> {
    private Long id1;
    private Long id2;
    private String text;
    private LocalDateTime date;

    public Message(Long id1, Long id2, String text, LocalDateTime date) {
        this.id1 = id1;
        this.id2 = id2;
        this.text = text;
        this.date = date;
    }

    public Long getId1() {
        return id1;
    }

    public Long getId2() {
        return id2;
    }

    public String getText() {
        return text;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public String toString() {
        return id1 + " -> " + id2 + " : '" + text + "' at " + date.toString();
    }
}
