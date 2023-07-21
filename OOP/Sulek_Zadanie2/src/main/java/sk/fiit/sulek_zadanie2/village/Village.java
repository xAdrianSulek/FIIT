package sk.fiit.sulek_zadanie2.village;

import sk.fiit.sulek_zadanie2.entity.Player;

/**
 * Class for finding a Village
 */

public class Village {
    Player player = Player.getInstance();

    /**
     * It will heal the player to the full health
     * and on return it will inform the observer
     * @return string which will go to inform the observer
     */
    public String heal(){
        player.setHp(player.getMaxHp());
        return player.getName() + "Has been fully healed";
    }
}
