#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //

// === هيكل بيانات السيارة ===
typedef struct {
    int vehicle_id;
    char owner_name[50];
    char plate_number[20];
    char vehicle_type[20];
    long entry_time; // الوقت بالثواني[cite: 1]
    int slot_number;
} Vehicle;

// === هيكل بيانات مكان الركنة ===
typedef struct {
    int slot_id;
    int is_occupied; // 0 لو متاح، 1 لو مشغول
} Slot;

// === المتغيرات والمصفوفات العامة (المشتركة بينكما) ===
extern Vehicle parking_list[100]; //[cite: 1]
extern Slot slots[20];            //[cite: 1]
extern int vehicle_count;         //[cite: 1]

// === الجزء الخاص بك أنت (الليدر) ===
void add_vehicle();            // إضافة سيارة[cite: 1]
void assign_slot(int id);      // حجز مكان للسيارة
double calculate_fees(long entry_time); // حساب الرسوم[cite: 1]

// === الجزء الخاص بصاحبك ===
void remove_vehicle();         // خروج وحذف السيارة والـ Shifting[cite: 1]
void display_overview();       // إحصائيات الجراج[cite: 1]
void save_to_file();           // حفظ في الملف
void load_from_file();         // تحميل من الملف

#endif