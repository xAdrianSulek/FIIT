package sk.fiit.sulek_zadanie2.entity;

import javafx.scene.image.Image;

import java.util.Objects;

/**
 * Third class that inherit
 */
public class Snake extends Enemy{

    int xp;
    public Snake(int hp, int dmg, int speed) {
        super(hp, dmg, speed);
        this.name = "Snake";
        this.imgName = "Images/snake.png";
        xp = 7;
    }

    public int getXp() {
        return xp;
    }
    /**
     * Internal overridden method which is called upon in combat
     * @param player
     */
    public void attack(Player player){
        if (hp > 0){
            player.setHp(player.getHp() - getDmg());
            if (getHp() < 0)
                setHp(0);
        }
    }
}