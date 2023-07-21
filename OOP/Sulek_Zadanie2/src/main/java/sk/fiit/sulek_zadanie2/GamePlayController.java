package sk.fiit.sulek_zadanie2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import sk.fiit.sulek_zadanie2.entity.Player;
import sk.fiit.sulek_zadanie2.game.Game;

import java.io.IOException;
import java.net.URL;
import java.util.Objects;
import java.util.ResourceBundle;

/**
 * class for controlling gameplay.fxml
 */
public class GamePlayController implements Initializable {

    Player player = Player.getInstance();
    Game game = new Game();
    Stats stats = new Stats();
    @FXML
    AnchorPane rootPane;

    @FXML
    Button startBtn;
    @FXML
    TextArea statTextArea;
    @FXML
    TextArea logTextArea;

    @FXML
    Label lbl;

    @FXML
    Image image;
    @FXML
    Image pathImage;


    @FXML
    Image tryImg;

    @FXML
    ImageView playerView;
    @FXML
    ImageView pathView;
    @FXML
    ImageView destView;

    /**
     *Clicking button will add observers to the observable
     *and check if the player is fighting or not
     *if not he will walk and reach new random destionation
     *if yes he will begin to fight enemy
     *updating the status window and image of destination and log trough observers
     * @throws IOException
     */
    @FXML
    public void onClickButton() throws IOException {
        ImageOfDest aImageOfDest = new ImageOfDest(game);
        Log log = new Log(game);
        game.obserLog(log);
        game.imageOfDest(aImageOfDest);
        if(!player.getInAction()){
            startBtn.setText("Continue");
            game.walk();
            tryImg = aImageOfDest.dajImg();
            destView.setImage(tryImg);
            statTextArea.setText(stats.dajString());
            logTextArea.setText(log.dajLogString());
            actionChekcer();
        }
        else {
            game.battle();
            statTextArea.setText(stats.dajString());
            logTextArea.setText(log.dajLogString());
            actionChekcer();
            if (player.getHp() <= 0){
                endScreen();
            }
        }
    }

    /**
     * Changing the inscription of the button
     */
    public void actionChekcer(){
        if (player.getInAction()){
            startBtn.setText("Fight");
        }
        else
            startBtn.setText("Contrinue");
    }

    /**
     * if player dies he will go to endScene.fxml
     * @throws IOException
     */
    public void endScreen() throws IOException {
        AnchorPane pane = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("endScene.fxml")));
        rootPane.getChildren().setAll(pane);
    }

    /**
     *initialize class which will activate upon initiliazing this function
     *adding chosen player image and raod to the GUI
     *adding first log message and status windown stats
     * @param url
     * @param resourceBundle
     */
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        image = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/char" + player.getChararr()[0]+player.getChararr()[1]+player.getChararr()[2]+".png")));
        pathImage = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/Path.png")));
        logTextArea.setText("You found yourself on a weird dirt path.\nWith old sword you begin your journey");
        pathView.setImage(pathImage);
        playerView.setImage(image);
        statTextArea.setText(stats.dajString());

    }
    @FXML
    protected void onExitButton(){
        Platform.exit();
    }

}
