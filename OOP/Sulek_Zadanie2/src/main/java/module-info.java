module sk.fiit.sulek_zadanie2 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens sk.fiit.sulek_zadanie2 to javafx.fxml;
    exports sk.fiit.sulek_zadanie2;
}