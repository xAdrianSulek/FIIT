package sk.fiit.sulek_zadanie2.entity;

import sk.fiit.sulek_zadanie2.weapon.RustySword;
import sk.fiit.sulek_zadanie2.weapon.Weapon;

import java.util.Random;

/**
 * Player character
 */
public class Player {

    /**
     * Setting this object to single instance
     */
    private static Player single_instance = null;

    /**
     * Atributes
     */
    private int hp;
    private int maxHp;
    private int dmg;
    private int speed;
    private int xp;
    private String name;
    private Boolean inAction = false;

    protected Weapon currentWeapon;
    private int[] chararr;

    private Player(int hp, int dmg,int speed, Weapon weapon){
        this.hp = hp;
        this.dmg = dmg;
        this.speed = speed;
        this.maxHp = hp;
        this.currentWeapon = weapon;
        xp = 0;
    }

    /**
     *Singleton
     *First time its called it is gonna create instance of player
     *Otherwise it will get the instance
     * @return the instance of player
     */
    public static synchronized Player getInstance(){
        if (single_instance == null)
            single_instance = new Player(100,4,4, new RustySword(1));
        return single_instance;
    }

    /**
     * Method for reseting for newGame
     */
    public void resetPlayer(){
        setXp(0);
        setHp(100);
        setDmg(4);
        setSpeed(4);
        setInAction(false);
        setCurrentWeapon(new RustySword(1));
    }

    /**
     * Getters and setters
     */

    public int getHp() {
        return hp;
    }

    public int getDmg() {
        return dmg;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setDmg(int dmg) {
        this.dmg = dmg;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public Boolean getInAction() {
        return inAction;
    }

    public void setInAction(Boolean inAction) {
        this.inAction = inAction;
    }

    public int getXp() {
        return xp;
    }

    public void setXp(int xp) {
        this.xp = xp;
    }


    public int[] getChararr() {
        return chararr;
    }

    public void setChararr(int[] chararr) {
        this.chararr = chararr;
    }

    public Weapon getCurrentWeapon() {
        return currentWeapon;
    }

    public void setCurrentWeapon(Weapon currentWeapon) {
        this.currentWeapon = currentWeapon;
    }

    public String getWeaponName(){
        return currentWeapon.getName();
    }
    public int getWeaponDamage(){
        return currentWeapon.getDmg();
    }

    /**
     * Method which is called in combat
     * @param enemy
     */
    public void attack(Enemy enemy){
        enemy.setHp(enemy.getHp() - (getDmg()+getWeaponDamage()));
        if (enemy.getHp() < 0){
            enemy.setHp(0);
        }
    }

    public int getMaxHp() {
        return maxHp;
    }

    /**
     * Method which generates random number between 0-10
     * @return random number between 0-10
     */
    public int walk(){
        Random random = new Random();
        return random.nextInt(11);
    }
}
