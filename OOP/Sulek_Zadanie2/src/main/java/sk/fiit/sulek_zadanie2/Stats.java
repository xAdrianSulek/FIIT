package sk.fiit.sulek_zadanie2;

import sk.fiit.sulek_zadanie2.entity.Player;

/**
 * Class which is updating GUI element for player stats in text windown
 */
public class Stats {
    String stat;
    Player player = Player.getInstance();

    /**
     * Method which will update the status window
     * @return combined string of the stats
     */
    public String dajString(){
        stat = player.getName() + "     Health: "+player.getHp() + "    Strength: "+player.getDmg() + "     Xp: "+player.getXp()
                + "\n\n" + player.getWeaponName() + "     Dmg: " + player.getWeaponDamage();
        return stat;
    }
}
