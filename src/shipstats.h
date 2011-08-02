/*
 * See Licensing and Copyright notice in naev.h
 */



#ifndef SHIPSTATS_H
#  define SHIPSTATS_H


#include "nxml.h"


/**
 * @brief Lists all the possible types.
 *
 * Syntax:
 *    SS_TYPE_#1_#2
 *
 * #1 is D for double, A for absolute double, I for integer or B for boolean.
 * #2 is the name.
 */
typedef enum ShipStatsType_ {
   SS_TYPE_NIL,               /**< Invalid type. */

   /*
    * D: Double type data. Should be continuous.
    */
   /* Freighter-type. */
   SS_TYPE_D_JUMP_DELAY,      /**< Modulates the time that passes during a hyperspace jump. */
   SS_TYPE_D_CARGO_INERTIA,   /**< Modifies the effect of cargo_mass. */

   /* Stealth. */
   SS_TYPE_D_EW_HIDE,         /**< Electronic warfare hide modifier. */
   SS_TYPE_D_EW_DETECT,       /**< Electronic warfare detection modifier. */

   /* Launchers. */
   SS_TYPE_D_LAUNCH_RATE,     /**< Launch rate for missiles. */  /* TODO */
   SS_TYPE_D_LAUNCH_RANGE,    /**< Launch range for missiles. */ /* TODO */
   SS_TYPE_D_AMMO_CAPACITY,   /**< Capacity of launchers. */     /* TODO */
   SS_TYPE_D_LAUNCH_LOCKON,   /**< Lockon speed of launchers. */ /* TODO */

   /* Forward mounts. */
   SS_TYPE_D_FORWARD_HEAT,    /**< Heat generation for cannons. */
   SS_TYPE_D_FORWARD_DAMAGE,  /**< Damage done by cannons. */
   SS_TYPE_D_FORWARD_FIRERATE, /**< Firerate of cannons. */
   SS_TYPE_D_FORWARD_ENERGY,  /**< Energy usage of cannons. */

   /* Turrets. */
   SS_TYPE_D_TURRET_HEAT,     /**< Heat generation for turrets. */
   SS_TYPE_D_TURRET_DAMAGE,   /**< Damage done by turrets. */
   SS_TYPE_D_TURRET_FIRERATE, /**< Firerate of turrets. */
   SS_TYPE_D_TURRET_ENERGY,   /**< Energy usage of turrets. */

   /* Nebula. */
   SS_TYPE_D_NEBULA_DMG_SHIELD, /**< Shield nebula resistance. */
   SS_TYPE_D_NEBULA_DMG_ARMOUR, /**< Armour nebula resistance. */

   /* Misc. */
   SS_TYPE_D_HEAT_DISSIPATION, /**< Ship heat dissipation. */

   /*
    * A: Absolute double type data. Should be continuous.
    */

   /*
    * I: Integer type data. Should be continuous.
    */

   /*
    * B: Boolean type data. Should be continuous.
    */
   SS_TYPE_B_INSTANT_JUMP, /**< Do not require brake or chargeup to jump. */

   SS_TYPE_SENTINAL,          /**< Sentinal for end of types. */
} ShipStatsType;

/**
 * @brief Represents relative ship statistics as a linked list.
 *
 * Doubles:
 *  These values are relative so something like -0.15 would be -15%.
 *
 * Absolute and Integers:
 *  These values are just absolute values.
 *
 * Booleans:
 *  Can only be 1.
 */
typedef struct ShipStatList_ {
   struct ShipStatList_ *next; /**< Next pointer. */

   int target;          /**< Whether or not it affects the target. */
   ShipStatsType type;  /**< Type of stat. */
   union {
      double d;         /**< Floating point data. */
      int    i;         /**< Integer data. */
   } d; /**< Stat data. */
} ShipStatList;


/**
 * @brief Represents ship statistics, properties ship can use.
 *
 * Doubles: 
 *  These are normalized and centered around 1 so they are in the [0:2]
 *  range, with 1. being default. This value then modulates the stat's base
 *  value.
 *  Example:
 *   0.7 would lower by 30% the base value.
 *   1.2 would increase by 20% the base value.
 *
 * Absolute and Integers:
 *  Absolute values in whatever units it's meant to use.
 *
 * Booleans:
 *  1 or 0 values wher 1 indicates property is set.
 */
typedef struct ShipStats_ {
#if 0
   /* Corvette type. */
   double afterburner_energy; /**< Energy used by afterburner. */

   /* Carrier type. */
   double fighterbay_cpu; /**< CPU usage by fighter bays. */
   double fighterbay_rate; /**< Launch rate of fighter bay. */
#endif

   /* Freighter-type. */
   double jump_delay;      /**< Modulates the time that passes during a hyperspace jump. */
   double cargo_inertia;   /**< Lowers the effect of cargo mass. */

   /* Stealth. */
   double ew_hide;         /**< Electronic warfare hide modifier. */
   double ew_detect;       /**< Electronic warfare detection modifier. */

   /* Military type. */
   double heat_dissipation; /**< Global ship dissipation. */

   /* Launchers. */
   double launch_rate;     /**< Fire rate of launchers. */
   double launch_range;    /**< Range of launchers. */
   double ammo_capacity;   /**< Capacity of launchers. */
   double launch_lockon;   /**< Lock on speed of launchers. */

   /* Fighter/Corvette type. */
   double fwd_heat;        /**< Heat of forward mounts. */
   double fwd_damage;      /**< Damage of forward mounts. */
   double fwd_firerate;    /**< Rate of fire of forward mounts. */
   double fwd_energy;      /**< Consumption rate of forward mounts. */

   /* Destroyer/Cruiser type. */
   double tur_heat;        /**< Heat of turrets. */
   double tur_damage;      /**< Damage of turrets. */
   double tur_firerate;    /**< Rate of fire of turrets. */
   double tur_energy;      /**< Consumption rate of turrets. */

   /* Misc. */
   double nebula_dmg_shield; /**< Shield nebula resistance. */
   double nebula_dmg_armour; /**< Armour nebula resistance. */
   int misc_instant_jump; /**< Do not require brake or chargeup to jump. */
} ShipStats;


/*
 * Safety.
 */
int ss_check (void);

/*
 * Loading.
 */
ShipStatList* ss_listFromXML( xmlNodePtr node );
void ss_free( ShipStatList *ll );

/*
 * Manipulation
 */
int ss_statsInit( ShipStats *stats );
int ss_statsModSingle( ShipStats *stats, const ShipStatList* list, const ShipStats *amount );
int ss_statsModFromList( ShipStats *stats, const ShipStatList* list, const ShipStats *amount );

/*
 * Lookup.
 */
const char* ss_nameFromType( ShipStatsType type );
ShipStatsType ss_typeFromName( const char *name );
int ss_statsListDesc( const ShipStatList *ll, char *buf, int len, int newline );
int ss_statsDesc( const ShipStats *s, char *buf, int len, int newline );


#endif /* SHIPSTATS_H */
