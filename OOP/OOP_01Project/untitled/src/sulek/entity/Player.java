package sulek.entity;

public class Player {

    String name;
    private int hp;
    private int dmg;
    private int speed;
    private int xp;
    public Player(int hp, int dmg, int speed){
        this.hp = hp;
        this.dmg = dmg;
        this.speed = speed;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setDmg(int dmg) {
        this.dmg = dmg;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHp() {
        return hp;
    }

    public int getDmg() {
        return dmg;
    }

    public int getSpeed() {
        return speed;
    }

    public String getName() {
        return name;
    }

    public void attack(Enemy enemy){
        enemy.hp -= dmg;
        if (hp < 0)
            setHp(0);
    }

    public Boolean escape(){
        if (Math.random() > 0.5)
            return true;
        else
            return false;
    }
}
