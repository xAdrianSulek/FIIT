package sk.fiit.sulek_zadanie2.game;

import sk.fiit.sulek_zadanie2.entity.Enemy;
import sk.fiit.sulek_zadanie2.entity.Player;

/**
 * Strategy interface for setting up a fight
 */
public interface StrategyCombat {

    void doBattle(Player player, Enemy enemy);
}
