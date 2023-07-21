package sk.fiit.sulek_zadanie2.entity;

import javafx.scene.image.Image;

/**
 * Abstract class of enemy
 */
public  abstract class Enemy {

    /**
     * Setting atributes the enemy will have
     *
     */
    int hp;
    int dmg;
    int speed;
    int xp;
    String name;
    String imgName;


    public Enemy(int hp, int dmg, int speed) {
        this.hp = hp;
        this.dmg = dmg;
        this.speed = speed;
    }

    public int getHp() {
        return hp;
    }

    public int getDmg() {
        return dmg;
    }

    public int getSpeed() {
        return speed;
    }

    public String getName() {
        return name;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDmg(int dmg) {
        this.dmg = dmg;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public String getImgName() {
        return imgName;
    }

    public int getXp() {
        return xp;
    }

    public void attack(Player player){}
}