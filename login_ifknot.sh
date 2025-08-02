#!/bin/bash
echo "SSH kitchen key for ifknot..."
ssh-add -D #strip old one(s) because Sonoma updated f**ked it all
ssh-add ~/.ssh/id_ed25519_kitchen
