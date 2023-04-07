package com.example.prosim;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;

import java.net.URL;
import java.util.ResourceBundle;

public class GameController {
    @FXML
    private AnchorPane pane;

    @FXML
    private TextArea combatLog;
    @FXML
    private TextArea scoreLog;

    @FXML
    protected void onAttackButton(){
        combatLog.setText("Attacked!");
    }

    @FXML
    protected void onEscapeButton(){
        combatLog.setText("Escaped!");
    }

}
