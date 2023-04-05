package fiit.sulek.demo;

import com.almasb.fxgl.dev.Console;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

import java.io.PrintStream;

public class HelloController {
    @FXML
    private Label welcomeText;
    @FXML
    private Label attackText;
    @FXML
    private TextArea console;
    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
    @FXML
     protected void onAttackButtonClick(){
        attackText.setText("Youve attacked");
     }

}