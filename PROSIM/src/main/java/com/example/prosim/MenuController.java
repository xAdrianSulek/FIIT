package com.example.prosim;

import com.example.prosim.entity.Player;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;
import java.net.URL;
import java.util.Objects;
import java.util.ResourceBundle;

public class MenuController {
    Player player = Player.getInstance();

    @FXML
    private AnchorPane rootPane;
    @FXML
    private TextField nameText1;

    @FXML
    protected void onHelloButtonClick() throws IOException {
        player.setName(nameText1.getText());
        System.out.println(player.getName());
        loadSecond();
    }

    @FXML
    private void loadSecond() throws IOException {
        AnchorPane pane = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("gameScene.fxml")));
        rootPane.getChildren().setAll(pane);
    }

}