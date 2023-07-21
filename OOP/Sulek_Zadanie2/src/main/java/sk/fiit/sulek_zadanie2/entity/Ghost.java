package sk.fiit.sulek_zadanie2.entity;

import javafx.scene.image.Image;

import java.util.Objects;

/**
 * First enemy that inherit from Enemy
 */
public class Ghost extends Enemy{

    public Ghost(int hp, int dmg, int speed) {
        super(hp, dmg, speed);
        this.name = "Ghost";
        this.imgName = "Images/ghost.png";
        xp = 12;
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
