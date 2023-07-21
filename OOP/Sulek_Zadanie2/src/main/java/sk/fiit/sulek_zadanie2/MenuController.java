package sk.fiit.sulek_zadanie2;



import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;


import java.io.IOException;
import java.util.Objects;


/**
 * Controller class for  menu.fxml
 */
public class MenuController {

    @FXML
    private AnchorPane rootPane;

    @FXML
    protected void onHelloButtonClick() throws IOException {
        loadSecond();
    }

    /**
     * Method for loading onto the next scene
     * @throws IOException
     */
    @FXML
    private void loadSecond() throws IOException {
        AnchorPane pane = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("characterScene.fxml")));
        rootPane.getChildren().setAll(pane);
    }
    @FXML
    protected void onExitButton(){
        Platform.exit();
    }

}