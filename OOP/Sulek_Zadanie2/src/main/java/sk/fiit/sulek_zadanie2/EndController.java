package sk.fiit.sulek_zadanie2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;
import sk.fiit.sulek_zadanie2.entity.Player;


import java.io.IOException;
import java.net.URL;
import java.util.Objects;
import java.util.ResourceBundle;

/**
 * class for controlling endScene.fxml
 */
public class EndController implements Initializable {

    Player player = Player.getInstance();

    @FXML
    protected AnchorPane rootPane;

    @FXML
    protected Text score;
    @FXML
    protected Text title;

    public void onExitButton(){
        Platform.exit();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        if (player.getHp()<=0)
            title.setText("DEFEATED");
        score.setText(String.valueOf(player.getXp()));
    }

    /**
     * if the player click the button the game will start again
     * @throws IOException
     */
    @FXML
    private void loadSecond() throws IOException {
        player.resetPlayer();
        AnchorPane pane = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("gameplayScene.fxml")));
        rootPane.getChildren().setAll(pane);
    }

}
