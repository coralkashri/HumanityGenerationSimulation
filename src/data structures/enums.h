#ifndef CIRCLESQUEREGAMEPROTOTYPE_ENUMS_H
#define CIRCLESQUEREGAMEPROTOTYPE_ENUMS_H

enum Methods {
    WAIT = 0,
    NEW_HOME = 1,
    ATTACK = 2,
    BUILD = 3
};

enum TriggerType {
    VISIT,
    CALL
};

enum class EventType {
    THOUGHTS,
    MEETS,
    BIRTHDAY,
    DEATH,
    KID_BORN,
    MARRIAGE,
    CALL,
    FRIENDSHIP_STARTED
};

enum class Emotions {
    LOVE,
    SYMPATHY,
    HATE,
    ANGRY,
    NOTHING,
    SAD
};

enum Gender {
    MALE = 1,
    FEMALE = 2
};

enum Role {
    POLICEMAN,
    DOCTOR,
    BAD,
    NOTHING_SPECIAL
};

enum Work {
    TEACHER,
    STUDENT,
    POLICE,
    HOSPITAL
};

enum HealthCondition {
    HEALTHY,
    VIRUS,
    SICK,
    VERY_SICK
};

enum Direction {
    RIGHT,
    LEFT,
    TOP,
    DOWN
};

enum Animals {
    BEAR,
    DOLPHIN,
    HIPO,
    PINGWIN,
    ZEBRA,
    HORSE,
    ELEPHENT,
    DOG,
    CAT,
    BIRD,
    SHARK,
    SNAKE,
    WOLF,
    BEE
};

#endif //CIRCLESQUEREGAMEPROTOTYPE_ENUMS_H
