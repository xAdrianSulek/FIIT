package sk.fiit.sulek_zadanie2.entity;

import javafx.scene.image.Image;

import java.util.Objects;

/**
 * Second enemy that inherit from Enemy
 */
public class Skeleton extends Enemy{

    public Skeleton(int hp, int dmg, int speed) {
        super(hp, dmg, speed);
        this.name = "Skeleton";
        this.imgName = "Images/skeleton.png";
        xp = 23;
    }
    public int getXp() {
        return xp;
    }

    /**
     * Internal overridden method which is called upon in combat
     * @param player
     */
    public void attack(Player player){
        player.setHp(player.getHp() - getDmg());
    }
}