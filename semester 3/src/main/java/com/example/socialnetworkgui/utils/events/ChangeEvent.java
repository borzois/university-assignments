package com.example.socialnetworkgui.utils.events;

import com.example.socialnetworkgui.domain.User;

public class ChangeEvent implements Event {
    private ChangeEventType type;
    public ChangeEvent(ChangeEventType type) {
        this.type = type;
    }

    public ChangeEventType getType() {
        return type;
    }
}