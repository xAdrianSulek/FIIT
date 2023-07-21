package sk.fiit.sulek_zadanie2;

import sk.fiit.sulek_zadanie2.weapon.Weapon;

/**
 * Observer interface for changing
 */
public interface ObserveLog {
    void update(int value, Weapon currentWeapon, Weapon chestWeapon);
}
