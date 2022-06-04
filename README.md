# Vail

Communicate using Morse

![vail window](.gitlab/vail.png)

## Build Flatpak

To build a flatpak bundle of Vail use the following instructions:

```bash
$ git clone https://invent.kde.org/fhek/vail.git
$ cd vail
$ flatpak-builder --repo=repo build-dir --force-clean org.kde.vail.json
$ flatpak build-bundle repo vail.flatpak org.kde.vail
```

Now you can either double-click the `vail.flatpak` file to open it with
some app store (discover, gnome-software, etc...) or run:

```bash
$ flatpak install vail.flatpak
```
