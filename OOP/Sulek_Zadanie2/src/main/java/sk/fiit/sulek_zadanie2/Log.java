package sk.fiit.sulek_zadanie2;

import sk.fiit.sulek_zadanie2.entity.Player;
import sk.fiit.sulek_zadanie2.game.Game;
import sk.fiit.sulek_zadanie2.weapon.Weapon;

/**
 * Observer for choosing log output
 */
public class Log implements ObserveLog {
    Player player = Player.getInstance();
    Game game;
    String strLog;

    public Log(Game game){
        this.game = game;
    }

    public String dajLogString(){
        return strLog;
    }

    /**
     * on update observer will change strLog as needed
     * @param value
     * @param currentWeapon
     * @param chestWeapon
     */
    @Override
    public void update(int value, Weapon currentWeapon, Weapon chestWeapon) {
        switch (value){
            case 1:
                strLog = "You've found a chest!\n\n";
                if (currentWeapon.getDmg() >= chestWeapon.getDmg()){
                    strLog += "Inside is "+chestWeapon.getName()+".\nThis weapons is not better.\nYou will keep your old";
                }
                else {
                    strLog += "Inside is " + chestWeapon.getName() + ".\nYou have equipped the sword!";
                    player.setCurrentWeapon(chestWeapon);
                }
                break;
            case 2:
                strLog = game.returnEnemyName()+"!\nFight it!";
                player.setInAction(true);
                break;
            case 3:
                strLog = "You've found a Village!\n\n";
                if (player.getHp() != player.getMaxHp()){
                    strLog += "Your health has been restored\nAnd you rest for the night";
                    player.setHp(player.getMaxHp());
                }
                else {
                    strLog +="Your health is full\nYou rest for the night";
                }
                break;
            case 4:
                strLog = "You've won!\nReceived "+game.returnXp()+" experience";

        }
    }

}
