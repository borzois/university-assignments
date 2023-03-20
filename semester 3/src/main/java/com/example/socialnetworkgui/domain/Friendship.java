package com.example.socialnetworkgui.domain;

import java.time.LocalDateTime;
import java.util.Objects;

public class Friendship extends Entity<Tuple<Long, Long>> {
    private User user1;
    private User user2;
    private LocalDateTime startDate;
    private Boolean accepted;
    private Boolean fromUser1;

    public Friendship(User user1, User user2, Boolean fromUser1) {
        this.user1 = user1;
        this.user2 = user2;
        startDate = LocalDateTime.now();
        accepted = false;
        this.fromUser1 = fromUser1;
    }

    public Friendship(User user1, User user2, LocalDateTime t, Boolean accepted, Boolean fromUser1) {
        this.user1 = user1;
        this.user2 = user2;
        this.startDate = t;
        this.accepted = accepted;
        this.fromUser1 = fromUser1;
    }

    public User getUser1() {
        return user1;
    }
    public String getRequesterName() {
        if (fromUser1) return user1.getName();
        return user2.getName();
    }
    public String getRequesteeName() {
        if (fromUser1) return user2.getName();
        return user1.getName();
    }

    public User getUser2() {
        return user2;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public Boolean getStatus() {
        return accepted;
    }

    public Boolean getDirection() {
        return fromUser1;
    }
    public void setStatus(Boolean accepted) {
        this.accepted = accepted;
    }

    @Override
    public String toString() {
        return user1 + " - " + user2 + " | since " + startDate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return (user1.equals(that.user1) && user2.equals(that.user2))
                || (user1.equals(that.user2) && user2.equals(that.user1));
    }

    @Override
    public int hashCode() {
        return Objects.hash(user1, user2);
    }

    public void accept() {
        if (!accepted) {
            accepted = true;
        }
    }
}
