module com.example.socialnetworkgui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;
    requires org.postgresql.jdbc;

    opens com.example.socialnetworkgui to javafx.fxml;
    opens com.example.socialnetworkgui.controller to javafx.fxml;
    opens com.example.socialnetworkgui.repository to javafx.fxml;
    opens com.example.socialnetworkgui.service to javafx.fxml;
    opens com.example.socialnetworkgui.domain to javafx.base;
    opens com.example.socialnetworkgui.ui to javafx.fxml;

    exports com.example.socialnetworkgui to javafx.graphics;


    requires javafx.base;
    requires javafx.graphics;
    requires org.kordamp.ikonli.core;
    requires org.kordamp.ikonli.javafx;
    // add icon pack modules
    requires org.kordamp.ikonli.antdesignicons;
    requires org.kordamp.ikonli.fluentui;
}