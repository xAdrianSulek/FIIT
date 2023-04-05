package sulek.entity;

public class Ghost extends Enemy{
    public Ghost(int hp, int dmg, int speed) {
        super(hp, dmg, speed);
        this.name = "Ghost";
    }
}
