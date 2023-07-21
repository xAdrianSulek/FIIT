package sk.fiit.sulek_zadanie2.game;

import sk.fiit.sulek_zadanie2.ObserveLog;
import sk.fiit.sulek_zadanie2.ObserverImage;
import sk.fiit.sulek_zadanie2.entity.*;
import sk.fiit.sulek_zadanie2.village.Village;
import sk.fiit.sulek_zadanie2.weapon.Weapon;

import java.util.ArrayList;
import java.util.Random;

/**
 * Game class extend exception for Error handling
 */
public class Game extends Exception {

    /**
     * Creating needed objects
     */
    Player player = Player.getInstance();
    Enemy enemy;
    Village village = new Village();
    Chest chest = new Chest();
    Combat combat = new Combat(this);

    /**
     * ArraiList with objects of the interface in it
     * Used as a observer
     */
    private ArrayList<ObserverImage> observerImages = new ArrayList<>();
    private ArrayList<ObserveLog> observeLogs = new ArrayList<>();

    /**
     * Needed method for observers to work
     */

    /**
     * Add new listener
     * @param observerImage
     */
    public void imageOfDest(ObserverImage observerImage){
        observerImages.add(observerImage);
    }

    /**
     * Inform the observer
     * @param value
     */
    public void informDest(int value){
        for (ObserverImage observerImage : observerImages)
            observerImage.update(value);
    }

    /**
     * Add new listener
     * @param observeLog
     */
    public void obserLog(ObserveLog observeLog){
        observeLogs.add(observeLog);
    }

    /**
     * inform the observer
     * @param value
     * @param currentWeapon
     * @param chestWeapon
     */
    public void informLog(int value, Weapon currentWeapon, Weapon chestWeapon){
        for (ObserveLog observeLog : observeLogs)
            observeLog.update(value, currentWeapon, chestWeapon);
    }

    /**
     * method which will generate next action based on random probability
     * Player can either find a chest with 5% chance, find an enemy with 70% chance
     * or find a village with 25% chance
     */
    public void walk(){
        /**
         * After walking it will inform the observers for GUI elements
         */
        int value = player.walk();
        if (value <= 1){
            informLog(1, player.getCurrentWeapon(), chest.createWeapon());
            informDest(1);
        }
        if(value >1 && value <= 8){
            enemy = EnemyChooser();
            informDest(2);
            informLog(2, player.getCurrentWeapon(), player.getCurrentWeapon());
        }
        if(value > 8){
            informLog(3, player.getCurrentWeapon(), player.getCurrentWeapon());
            informDest(3);
        }
    }

    /**
     * Method for putting a player and enemy for battle
     */
    public void battle(){
        combat.doBattle(player,enemy);
    }

    /**
     * Method which will pick a random enemy out of 3 and return it
     * @return new random enemy out of 3
     */
    public Enemy EnemyChooser(){
        Random random = new Random();
        Enemy snake = new Snake(17,3,2);
        Enemy ghost = new Ghost(48,4,8);
        Enemy skeleton = new Skeleton(28,6,4);
        ArrayList<Enemy> enemyArrayList = new ArrayList<>();
        enemyArrayList.add(snake);
        enemyArrayList.add(ghost);
        enemyArrayList.add(skeleton);
        enemy = enemyArrayList.get(random.nextInt(enemyArrayList.size()));
        return enemy;
    }

    /**
     * inbetween methods for getting names, images or xp of enemy
     */
    public String returnImgString(){
        return enemy.getImgName();
    }

    public String returnEnemyName(){
        return enemy.getName();
    }

    public int returnXp(){
        return enemy.getXp();
    }



}
