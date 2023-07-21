package sk.fiit.sulek_zadanie2.weapon;

public abstract class Weapon {
    private int dmg;
    private String name;

    public Weapon(int dmg){
        this.dmg = dmg;
    }

    public int getDmg() {
        return dmg;
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
}
