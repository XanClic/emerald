#ifndef _KASSERT_H
#define _KASSERT_H

// FIXME: Vielleicht eine plattformspezifische RED-ALERT-Funktion einführen?

// kassert_exec wird die Kondition auch bei NDEBUG noch auswerten (im Gegensatz zum normalen assert)
#define kassert_exec(cond) do { if (!(cond)) for (;;); } while (0)
#define kassert(cond)      do { if (!(cond)) for (;;); } while (0)

#endif
