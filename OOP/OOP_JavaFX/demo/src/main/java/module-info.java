module fiit.sulek.demo {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;
    requires com.almasb.fxgl.all;

    opens fiit.sulek.demo to javafx.fxml;
    exports fiit.sulek.demo;
}