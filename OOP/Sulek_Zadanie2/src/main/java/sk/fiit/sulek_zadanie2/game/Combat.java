package sk.fiit.sulek_zadanie2.game;

import sk.fiit.sulek_zadanie2.entity.Enemy;
import sk.fiit.sulek_zadanie2.entity.Player;

/**
 * Combat class
 */
public class Combat implements StrategyCombat{
    Game game;
    public Combat(Game game){
        this.game = game;
    }

    /**
     * Method which will take Player and a Enemy for a battle
     * @param player
     * @param enemy
     */
    @Override
    public void doBattle(Player player, Enemy enemy) {
        /**
         * it will loop until player or enemy has 0 health
         */
        while (player.getHp() > 0 && enemy.getHp() > 0){
            player.attack(enemy);
            enemy.attack(player);
            System.out.println(player.getHp()+"   "+ enemy.getHp());
        }
        /**
         * If enemy has 0 health, it will give you enemy XP and inform the observer
         */
        if (enemy.getHp() <= 0){
            player.setXp(player.getXp() + enemy.getXp());
            player.setInAction(false);
            game.informLog(4, player.getCurrentWeapon(), player.getCurrentWeapon());
        }
    }
}
