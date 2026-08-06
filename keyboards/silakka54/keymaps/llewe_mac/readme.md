# llewe_mac (silakka54)

macOS-Variante von `llewe`. Der Host muss auf **Deutsch (macOS)** stehen.

## Was gegenüber `llewe` geändert wurde

### Option-Ebene (der eigentliche Grund für dieses Keymap)

Die Grundpositionen der deutschen macOS-Belegung sind identisch mit der
PC-Belegung, nur die AltGr-/Option-Ebene weicht ab:

| Zeichen | Win/Linux DE | macOS DE      |
| ------- | ------------ | ------------- |
| `@`     | AltGr+Q      | ⌥L            |
| `~`     | AltGr++      | ⌥N (dead key) |
| `\`     | AltGr+ß      | ⇧⌥7           |
| `\|`    | AltGr+<      | ⌥7            |
| `{`     | AltGr+7      | ⌥8            |
| `}`     | AltGr+0      | ⌥9            |
| `[`     | AltGr+8      | ⌥5            |
| `]`     | AltGr+9      | ⌥6            |

Als Option-Modifier wird `KC_ALGR` (rechtes Alt) verwendet, damit die linke
Daumen-Option-Taste für normale Shortcuts frei bleibt.

### Dead Keys

` ` `, `~` und `^` sind unter macOS Dead Keys. Sie werden hier automatisch
mit einem nachfolgenden Leerzeichen aufgelöst, geben also direkt das Zeichen
aus. Wer das nicht will, entfernt `MAC_DEAD_ESC()` in `keymap.c`.

### Modifier / Navigation

- Daumenreihe: `LALT` / `LGUI` getauscht, damit ⌘ direkt neben der Leertaste
  liegt (wie auf einer Mac-Tastatur).
- `Home` / `End` → `⌘←` / `⌘→`.
- `PrintScreen` → `⇧⌘4` (Bildschirmfoto-Auswahl).

### Unicode

`config.h` setzt `UNICODE_SELECTED_MODES UNICODE_MODE_MACOS`. Damit
`send_unicode_string()` (Shrug-Macro, UCIS-Emojis) funktioniert, muss unter
**Systemeinstellungen → Tastatur → Eingabequellen** die Quelle
*Unicode Hex Input* hinzugefügt sein.

### Eigener Keycode `LL_BSLS`

Der Userspace (`users/spacebarracecar`) kodiert `CU_BSLS` fest mit den
PC-Sequenzen. Deshalb nutzt dieses Keymap ein eigenes `LL_BSLS`. Alle
anderen `CU_*`-Keys aus dem Userspace erzeugen unter macOS dieselben
Zeichen wie unter Windows/Linux und wurden unverändert übernommen.

## Falls `<` und `>` nicht funktionieren

`<` / `>` liegen unter macOS – genau wie unter Windows/Linux – auf
`KC_NUBS`, der ISO-Taste neben der linken Shift. Wenn nichts (oder das
falsche Zeichen) kommt, hat macOS die Tastatur als **ANSI** erkannt.

Fix: **Systemeinstellungen → Tastatur → Tastaturtyp ändern…** und im
Assistenten die Tastatur als **ISO (europäisch)** identifizieren. Der
Assistent lässt die Taste rechts neben der linken Shift drücken – dort
liegt auf diesem Board `Y`/`Z`, der Typ lässt sich aber am Ende manuell
auswählen.

## Bauen

```sh
qmk compile -kb silakka54 -km llewe_mac
```
