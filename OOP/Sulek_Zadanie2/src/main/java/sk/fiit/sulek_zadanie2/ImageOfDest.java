package sk.fiit.sulek_zadanie2;

import javafx.scene.image.Image;
import sk.fiit.sulek_zadanie2.entity.Enemy;
import sk.fiit.sulek_zadanie2.entity.Snake;
import sk.fiit.sulek_zadanie2.game.Game;

import java.util.Objects;

/**
 * Observer for updating Image in the destionation
 */
public class ImageOfDest implements ObserverImage {
    private Game game;
    Image chestImg = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/chest.png")));
    Image villageImg = new Image(Objects.requireNonNull(getClass().getResourceAsStream("Images/Village.png")));
    Image enemyImg;
    Image newImage;
    String imgString;

    
    public ImageOfDest(Game game){
        this.game = game;
    }

    Image dajImg(){
        return newImage;
    }

    public void getStr(){
        imgString = game.returnImgString();
        enemyImg = new Image(Objects.requireNonNull(getClass().getResourceAsStream(imgString)));
    }

    /**
     * based on the observable it will set new image
     * @param value
     */
    @Override
    public void update(int value) {
        switch (value) {
            case 1:
                this.newImage = this.chestImg;
                break;
            case 2:
                getStr();
                this.newImage = enemyImg;
                break;
            case 3:
                this.newImage = this.villageImg;
                break;
        }
    }
}
