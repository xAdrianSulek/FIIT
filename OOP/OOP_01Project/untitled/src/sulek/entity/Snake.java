package sulek.entity;

public class Snake extends Enemy{

    public Snake(int hp, int dmg, int speed) {
        super(hp, dmg, speed);
        this.name = "Snake";
    }

    public void attack(Player player){
        player.setHp(player.getHp() - getDmg());
        if (getHp() < 0)
            setHp(0);
    }
}
