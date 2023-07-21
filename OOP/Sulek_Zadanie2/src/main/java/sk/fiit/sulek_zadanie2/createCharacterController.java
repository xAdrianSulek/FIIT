package sk.fiit.sulek_zadanie2;

import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import sk.fiit.sulek_zadanie2.entity.Player;

import java.io.IOException;
import java.net.URL;
import java.util.Objects;
import java.util.Random;
import java.util.ResourceBundle;

/**
 * class for controling characterScene.fxml
 * Player can create hiw own character
 */
public class createCharacterController implements Initializable {
    Player player = Player.getInstance();
    @FXML
    protected AnchorPane rootPane;
    @FXML
    ImageView imageView;

    @FXML
    Slider HairSlider;
    @FXML
    Slider FaceSlider;
    @FXML
    Slider AcessSlider;

    /**
     *Number array which will represent the character
     *I've created 81 different character variations,
     *[0] goes for hair style
     *[1] goes for face
     *[2] goes for accesorie
     * there are 4 types in each and player can combine them
     */
    int[] charakter2 = new int[]{0,0,0};

    @FXML
    private TextField nameText1;

    /**
     * Method for loading to the game
     * @throws IOException
     */
    @FXML
    protected void onHelloButtonClick() throws IOException {
        player.setName(nameText1.getText());
        player.setChararr(charakter2);
        loadSecond();
    }

    @FXML
    Image ADAD = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/char"+charakter2[0]+charakter2[1]+charakter2[2]+".png")));



    int hairNumber;
    int faceNumber;
    int accesNumber;

    /**
     * Intiliaze method for the change in character creation
     * @param url
     * @param resourceBundle
     */
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        /**
         * The overridden methos act as a event listener, everytime player moves slider
         * It will change int value for its purpose and instantly change the player model
         */

        HairSlider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number number, Number t1) {
                hairNumber = (int) HairSlider.getValue();
                charakter2[0] = hairNumber;
                ADAD = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/char"+charakter2[0]+charakter2[1]+charakter2[2]+".png")));
                imageView.setImage(ADAD);
            }
        });

        FaceSlider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number number, Number t1) {
                faceNumber = (int) FaceSlider.getValue();
                charakter2[1] = faceNumber;
                ADAD = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/char"+charakter2[0]+charakter2[1]+charakter2[2]+".png")));
                imageView.setImage(ADAD);
            }
        });

        AcessSlider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number number, Number t1) {
                accesNumber = (int) AcessSlider.getValue();
                charakter2[2] = accesNumber;
                ADAD = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/char"+charakter2[0]+charakter2[1]+charakter2[2]+".png")));
                imageView.setImage(ADAD);
            }
        });

    }

    @FXML
    private void loadSecond() throws IOException {
        AnchorPane pane = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("gamePlayScene.fxml")));
        rootPane.getChildren().setAll(pane);
    }

    @FXML
    protected void onExitButton(){
        Platform.exit();
    }


}
