package sk.fiit.sulek_zadanie2.game;

import sk.fiit.sulek_zadanie2.entity.Player;
import sk.fiit.sulek_zadanie2.weapon.*;

import java.util.Random;

/**
 * Class which will generate new random weapon upon opening
 */
public class Chest {
    Game game;
    Weapon chestWeapon;
    Weapon currentWeapon;
    Player player = Player.getInstance();

    public Chest(){

    }

    /**
     * Method which will create new upon with random %chance
     * @return new Weapon
     */
    public Weapon createWeapon(){
        Random random = new Random();
        int chance = random.nextInt(11);
        if (chance <= 2){
            chestWeapon = new Excalibur(10);
        }
        if (chance > 2 && chance <= 5) {
            chestWeapon = new IronSword(3);
        }
        if (chance > 5 && chance <= 8){
            chestWeapon = new SilverMace(5);
        }
        if (chance > 8){
            chestWeapon = new RustySword(1);
        }
        return chestWeapon;
    }
}
