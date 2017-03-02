DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS posts;
DROP TABLE IF EXISTS communites;
DROP TABLE IF EXISTS modules;
DROP TABLE IF EXISTS community_modules;

CREATE TABLE users (
    id BIGINT(18) UNSIGNED NOT NULL PRIMARY KEY,
    name VARCHAR(32) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    pass VARCHAR(256) NOT NULL, 
    email VARCHAR(64) NOT NULL,
    verified BIT(1) NULL DEFAULT b'0',
    friend_id INT(5) UNSIGNED NOT NULL,
    joined DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    avatar VARCHAR(256) DEFAULT '' COLLATE 'utf8mb4_unicode_ci'
    friends TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8mb4_unicode_ci',
    pending TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8mb4_unicode_ci',
    blacklist TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8mb4_unicode_ci'
)
COLLATE='utf8mb4_unicode_ci'
ENGINE=InnoDB
;

CREATE TABLE posts (
    id BIGINT(18) UNSIGNED NOT NULL PRIMARY KEY,
    user_id BIGINT(18) UNSIGNED NOT NULL,
    chat_id BIGINT(18) UNSIGNED NOT NULL,
    posted DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    message VARCHAR(5000) NOT NULL COLLATE 'utf8mb4_unicode_ci'
)
COLLATE='utf8mb4_unicode_ci'
ENGINE=InnoDB
;

CREATE TABLE modules (
    id BIGINT(18) UNSIGNED NOT NULL PRIMARY KEY,
    icon VARCHAR(256) NULL
      DEFAULT 'https://goo.gl/T2Il9j'
      COLLATE 'utf8mb4_unicode_ci',
    url VARCHAR(256) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    name VARCHAR(32) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    author VARCHAR(32) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    verified BIT(1) NULL DEFAULT b'0',
    version VARCHAR(16) NULL DEFAULT 'alpha 0.0.0',
    description VARCHAR(1024) NOT NULL COLLATE 'utf8mb4_unicode_ci'
)
COLLATE='utf8mb4_unicode_ci'
ENGINE=InnoDB
;

CREATE TABLE communities (
    id BIGINT(18) UNSIGNED NOT NULL PRIMARY KEY,
    name VARCHAR(32) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    icon VARCHAR(256) DEFAULT '' COLLATE 'utf8mb4_unicode_ci',
    join_url VARCHAR(256) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    tags TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8_unicode_ci',
    bans TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8mb4_unicode_ci'
    settings TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8_unicode_ci',
    description VARCHAR(1024) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    s_description VARCHAR(128) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    members TEXT NOT NULL DEFAULT '{}',
    modules TEXT NOT NULL DEFAULT '{}',
    owner BIGINT(18) UNSIGNED NOT NULL,
    private BIT(1) NULL DEFAULT b'0',
    created DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
)
COLLATE='utf8mb4_unicode_ci'
ENGINE=InnoDB
;

CREATE TABLE community_modules (
    id BIGINT(18) UNSIGNED NOT NULL PRIMARY KEY,
    module_id BIGINT(18) UNSIGNED NOT NULL,
    name VARCHAR(32) NOT NULL COLLATE 'utf8mb4_unicode_ci',
    version VARCHAR(16) NULL DEFAULT 'alpha 0.0.0',
    settings TEXT NOT NULL DEFAULT '{}' COLLATE 'utf8_unicode_ci',
    added TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    sizex DOUBLE UNSIGNED NOT NULL,
    sizey DOUBLE UNSIGNED NOT NULL
)
COLLATE='utf8mb4_unicode_ci'
ENGINE=InnoDB
;