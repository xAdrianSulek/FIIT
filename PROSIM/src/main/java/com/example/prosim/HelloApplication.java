package com.example.prosim;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {


    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("menu.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 420, 360);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();


        /*stage.setTitle("DD");
        Label labelfirst = new Label("Enter your name");
        Label label = new Label();

        Button button=new Button("Submit");
        TextField text = new TextField();
        button.setOnAction(e ->
                {
                    label.setText("Tge bane you entered is" + text.getText());
                }
        );

        VBox layout = new VBox();

        layout.getChildren().addAll(labelfirst,text,button,label);

        Scene scene1 = new Scene(layout,200,250);
        stage.setScene(scene1);

        stage.show();*/
    }

    public static void main(String[] args) {
        launch();
    }

}